/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_CHART2_SOURCE_CONTROLLER_INC_DLG_CREATIONWIZARD_UNO_HXX
#define INCLUDED_CHART2_SOURCE_CONTROLLER_INC_DLG_CREATIONWIZARD_UNO_HXX

#include <MutexContainer.hxx>
#include <cppuhelper/component.hxx>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/XTerminateListener.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>

#include "dlg_CreationWizard.hxx"

namespace com::sun::star::awt { class XWindow; }
namespace com::sun::star::frame { class XModel; }
namespace com::sun::star::uno { class XComponentContext; }

class VclWindowEvent;

namespace chart
{

class CreationWizardUnoDlg : public MutexContainer
                            , public ::cppu::OComponentHelper
                            , public css::ui::dialogs::XExecutableDialog
                            , public css::lang::XServiceInfo
                            , public css::lang::XInitialization
                            , public css::frame::XTerminateListener
                            , public css::beans::XPropertySet
{
public:
    CreationWizardUnoDlg() = delete;

    CreationWizardUnoDlg( const css::uno::Reference< css::uno::XComponentContext >& xContext );
    virtual ~CreationWizardUnoDlg() override;

    // XInterface
    virtual css::uno::Any SAL_CALL queryInterface( const css::uno::Type& aType ) override;
    virtual css::uno::Any SAL_CALL queryAggregation( css::uno::Type const & rType ) override;
    virtual void SAL_CALL acquire() throw () override;
    virtual void SAL_CALL release() throw () override;

    // XTypeProvider
    virtual css::uno::Sequence< css::uno::Type > SAL_CALL getTypes(  ) override;
    virtual css::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId(  ) override;

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() override;
    virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) override;
    virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames() override;

    // XExecutableDialog
    virtual void SAL_CALL setTitle( const OUString& aTitle ) override;
    virtual sal_Int16 SAL_CALL execute(  ) override;

    // XInitialization
    virtual void SAL_CALL initialize( const css::uno::Sequence< css::uno::Any >& aArguments ) override;

    // XTerminateListener
    virtual void SAL_CALL queryTermination( const css::lang::EventObject& Event ) override;
    virtual void SAL_CALL notifyTermination( const css::lang::EventObject& Event ) override;

    virtual void SAL_CALL disposing( const css::lang::EventObject& Source ) override;

    //XPropertySet
    virtual css::uno::Reference< css::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) override;
    virtual void SAL_CALL setPropertyValue( const OUString& aPropertyName, const css::uno::Any& aValue ) override;
    virtual css::uno::Any SAL_CALL getPropertyValue( const OUString& PropertyName ) override;
    virtual void SAL_CALL addPropertyChangeListener( const OUString& aPropertyName, const css::uno::Reference< css::beans::XPropertyChangeListener >& xListener ) override;
    virtual void SAL_CALL removePropertyChangeListener( const OUString& aPropertyName, const css::uno::Reference< css::beans::XPropertyChangeListener >& aListener ) override;
    virtual void SAL_CALL addVetoableChangeListener( const OUString& PropertyName, const css::uno::Reference< css::beans::XVetoableChangeListener >& aListener ) override;
    virtual void SAL_CALL removeVetoableChangeListener( const OUString& PropertyName, const css::uno::Reference< css::beans::XVetoableChangeListener >& aListener ) override;

protected:
    // ____ OComponentHelper ____
    /// Called in dispose method after the listeners were notified.
    virtual void SAL_CALL disposing() override;

private:
    void createDialogOnDemand();

private:
    css::uno::Reference< css::frame::XModel >            m_xChartModel;
    css::uno::Reference< css::uno::XComponentContext>    m_xCC;
    css::uno::Reference< css::awt::XWindow >             m_xParentWindow;

    std::unique_ptr<CreationWizard> m_xDialog;
    bool            m_bUnlockControllersOnExecute;
};

} //namespace chart
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
