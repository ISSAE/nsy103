/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.cofares;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author pascalfares
 */
@Entity
@Table(name = "Dep")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Dep.findAll", query = "SELECT d FROM Dep d"),
    @NamedQuery(name = "Dep.findByIdDep", query = "SELECT d FROM Dep d WHERE d.idDep = :idDep"),
    @NamedQuery(name = "Dep.findByDepcol", query = "SELECT d FROM Dep d WHERE d.depcol = :depcol")})
public class Dep implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "idDep")
    private Integer idDep;
    @Basic(optional = false)
    @Column(name = "Depcol")
    private String depcol;
    @OneToMany(mappedBy = "idDep")
    private List<Emp> empList;

    public Dep() {
    }

    public Dep(Integer idDep) {
        this.idDep = idDep;
    }

    public Dep(Integer idDep, String depcol) {
        this.idDep = idDep;
        this.depcol = depcol;
    }

    public Integer getIdDep() {
        return idDep;
    }

    public void setIdDep(Integer idDep) {
        this.idDep = idDep;
    }

    public String getDepcol() {
        return depcol;
    }

    public void setDepcol(String depcol) {
        this.depcol = depcol;
    }

    @XmlTransient
    public List<Emp> getEmpList() {
        return empList;
    }

    public void setEmpList(List<Emp> empList) {
        this.empList = empList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idDep != null ? idDep.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Dep)) {
            return false;
        }
        Dep other = (Dep) object;
        if ((this.idDep == null && other.idDep != null) || (this.idDep != null && !this.idDep.equals(other.idDep))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "net.cofares.Dep[ idDep=" + idDep + " ]";
    }
    
}
